#include "VisualUtilities.h"




void DrawGridWithLabelsMeters(float pixelsPerMeter, Color majorLineColor, Color labelColor)
{
    int fontSize = 10;

    const int majorStepMeters = 50;
    const int minorStepMeters = 10;

    Color minorLineColor = Fade(majorLineColor, 0.3f);  // lighter color for sub-lines

    // Calculate visible world bounds (in meters)
    float leftMeters = 0.0f;
    float rightMeters = graphArea.width / pixelsPerMeter;
    float bottomMeters = 0.0f;
    float topMeters = graphArea.height / pixelsPerMeter;

    // Start drawing from the nearest lower multiple of step
    int startXMeters = (int)(leftMeters / minorStepMeters) * minorStepMeters;
    int endXMeters = (int)(rightMeters / minorStepMeters + 1) * minorStepMeters;

    int startYMeters = (int)(bottomMeters / minorStepMeters) * minorStepMeters;
    int endYMeters = (int)(topMeters / minorStepMeters + 1) * minorStepMeters;

    // Minor vertical lines
    for (int xMeters = startXMeters; xMeters <= endXMeters; xMeters += minorStepMeters) {
        float xPixel = graphArea.x + xMeters * pixelsPerMeter;
        DrawLine((int)xPixel, graphArea.y, (int)xPixel, graphArea.y + graphArea.height, minorLineColor);
    }

    // Minor horizontal lines
    for (int yMeters = startYMeters; yMeters <= endYMeters; yMeters += minorStepMeters) {
        float yPixel = graphArea.y + graphArea.height - yMeters * pixelsPerMeter; // invert Y
        DrawLine((int)graphArea.x, (int)yPixel, (int)(graphArea.x + graphArea.width), (int)yPixel, minorLineColor);
    }

    // Major vertical lines + labels
    for (int xMeters = startXMeters; xMeters <= endXMeters; xMeters += majorStepMeters) {
        float xPixel = graphArea.x + xMeters * pixelsPerMeter;
        DrawLine((int)xPixel, graphArea.y, (int)xPixel, graphArea.y + graphArea.height, majorLineColor);
        DrawText(TextFormat("%dm", xMeters), (int)xPixel + 2, graphArea.y + 5, fontSize, labelColor);
    }

    // Major horizontal lines + labels
    for (int yMeters = startYMeters; yMeters <= endYMeters; yMeters += majorStepMeters) {
        float yPixel = graphArea.y + graphArea.height - yMeters * pixelsPerMeter;
        DrawLine((int)graphArea.x, (int)yPixel, (int)(graphArea.x + graphArea.width), (int)yPixel, majorLineColor);
        DrawText(TextFormat("%dm", yMeters), graphArea.x + 5, (int)yPixel - fontSize / 2, fontSize, labelColor);
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
    float zoomStep = 0.1f;

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

