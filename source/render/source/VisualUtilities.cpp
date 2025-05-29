#include "VisualUtilities.h"



void DrawGridWithLabelsMeters(float pixelsPerMeter, Color majorLineColor, Color labelColor)
{
    int screenWidth = graphArea.width + graphArea.x;
    int screenHeight = graphArea.height +graphArea.y;
    int fontSize = 5;

    const int majorStepMeters = 50;
    const int minorStepMeters = 10;

    int majorSpacing = (int)(pixelsPerMeter * majorStepMeters);
    int minorSpacing = (int)(pixelsPerMeter * minorStepMeters);

    Color minorLineColor = Fade(majorLineColor, 0.3f);  // lighter color for sub-lines

    // Minor vertical lines (every 10m)
    for (int x = 0; x <= screenWidth; x += minorSpacing) {
        DrawLine(x, 0, x, screenHeight, minorLineColor);
    }

    // Minor horizontal lines (every 10m)
    for (int y = 0; y <= screenHeight; y += minorSpacing) {
        DrawLine(0, y, screenWidth, y, minorLineColor);
    }

    // Major horizontal lines + labels (every 50m)
    for (int x = 0; x <= screenWidth; x += majorSpacing) {
        DrawLine(x, 0, x, screenHeight, majorLineColor);
        int metersX = (int)(x / pixelsPerMeter);
        DrawText(TextFormat("%dm", metersX),x, 20, fontSize, labelColor);
    }

    // Major vertical lines + labels (every 50m)
    for (int y = 0; y <= screenHeight; y += majorSpacing) {
        DrawLine(0, screenHeight - y, screenWidth, screenHeight - y, majorLineColor);
        int metersY = (int)(y / pixelsPerMeter);
        DrawText(TextFormat("%dm", metersY), 20, screenHeight -y , fontSize, labelColor);
    }
}

void AdjustZoom(float& pixelsPerMeter, float zoomAmount)
{
    pixelsPerMeter += zoomAmount;
    const float minZoom =1.0f;
    const float maxZoom = 2000.0f;

    // Clamp to min/max zoom levels
    if (pixelsPerMeter < minZoom) pixelsPerMeter = minZoom;
    if (pixelsPerMeter > maxZoom) pixelsPerMeter = maxZoom;
}

void HandleZoomInput(float& pixelsPerMeter)
{
    float zoomStep = 0.5f;

    // Mouse wheel zoom
    int wheelMove = GetMouseWheelMove();
    if (wheelMove != 0)
    {
        AdjustZoom(pixelsPerMeter, wheelMove * zoomStep);
    }

    // Or keys: + to zoom in, - to zoom out
    if (IsKeyDown(KEY_KP_ADD) || IsKeyDown(KEY_EQUAL))  // '=' key near backspace
    {
        AdjustZoom(pixelsPerMeter, zoomStep);
    }
    if (IsKeyDown(KEY_KP_SUBTRACT) || IsKeyDown(KEY_MINUS))
    {
        AdjustZoom(pixelsPerMeter, -zoomStep);
    }
}

