#pragma once

#include "render/scene/node.h"
#include "ui/palette.h"
#include "ui/signal.h"

#include <optional>

class RectNode;

enum class ProgressBarOrientation {
  Horizontal,
  HorizontalCentered,
  Vertical,
};

class ProgressBar : public Node {
public:
  ProgressBar();

  void setFill(const ColorSpec& color);
  void setFill(const Color& color);
  void setTrack(const ColorSpec& color);
  void setTrack(const Color& color);
  void setFillColor(const ColorSpec& color);
  void setFillColor(const Color& color);
  void setTrackColor(const ColorSpec& color);
  void setTrackColor(const Color& color);
  void setRadius(float radius);
  void setSoftness(float softness);
  void setOrientation(ProgressBarOrientation orientation);

  // Optional reference marker drawn on top of the track and fill (e.g. an
  // expected progress position or a threshold). `marker` is a 0.0-1.0 position
  // along the track axis - 0.0 at the track start (left edge for the horizontal
  // orientations, bottom for vertical), 1.0 at the far end - independent of how
  // the fill grows, so it stays well-defined for HorizontalCentered where the
  // fill expands from the center. A negative (or NaN) value or clearMarker()
  // hides it.
  void setMarker(float marker);
  void clearMarker();
  void setMarkerColor(const ColorSpec& color);
  void setMarkerColor(const Color& color);
  // Thickness of the marker bar, in logical px. Hosts pass an already scaled
  // value, mirroring setSize()/setRadius().
  void setMarkerWidth(float width);

  void setProgress(float progress); // 0.0–1.0
  [[nodiscard]] float progress() const noexcept { return m_progress; }

  void setSize(float width, float height) override;

private:
  void applyPalette();
  void updateGeometry();

  RectNode* m_track = nullptr;
  Node* m_fillClip = nullptr;
  RectNode* m_fill = nullptr;
  RectNode* m_marker = nullptr;
  ColorSpec m_trackColor = colorSpecFromRole(ColorRole::SurfaceContainer);
  ColorSpec m_fillColor = colorSpecFromRole(ColorRole::Primary);
  ColorSpec m_markerColor = colorSpecFromRole(ColorRole::OnSurfaceVariant);
  std::optional<float> m_markerPos; // 0.0-1.0 along the track axis; nullopt = hidden
  float m_markerWidth = 2.0F;       // logical px thickness
  float m_progress = 1.0F;
  ProgressBarOrientation m_orientation = ProgressBarOrientation::Horizontal;
  Signal<>::ScopedConnection m_paletteConn;
};
