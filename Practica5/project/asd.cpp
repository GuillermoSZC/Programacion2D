


/*

bool Collider::checkCirclePixels(const Vec2& circlePos, float circleRadius, const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels) const
{
    float fCircleSize = circleRadius * 2;
    Vec2 fCirclePosTopLeft = Vec2(circlePos.GetX() - circleRadius, circlePos.GetY() - circleRadius);
    // Return false si los rectangulos no solapan
    if (!checkRectRect(pixelsPos, pixelsSize, fCirclePosTopLeft, Vec2(fCircleSize, fCircleSize)))
    {
        return false;
    }

    // Rectangulo que solapa
    float fPosX = (pixelsPos.GetX() < fCirclePosTopLeft.GetX()) ? fCirclePosTopLeft.GetX() : pixelsPos.GetX();
    float fWidth = std::fminf(pixelsPos.GetX() + pixelsSize.GetX(), fCirclePosTopLeft.GetX() + fCircleSize) - fPosX;
    float fPosY = (pixelsPos.GetY() < fCirclePosTopLeft.GetY()) ? fCirclePosTopLeft.GetY() : pixelsPos.GetY();
    float fHeight = std::fminf(pixelsPos.GetY() + pixelsSize.GetY(), fCirclePosTopLeft.GetY() + fCircleSize) - fPosY;
    //lgfx_setcolor(255, 0, 0, 255);
    //lgfx_drawrect(fPosX, fPosY, fWidth, fHeight);

    // Iteramos por el rectangulo que solapa
    int iPixelPosX = 0;
    int iPixelPosY = 0;
    int iIndexPixel = 0;
    Vec2 oDistancePixelCircle = Vec2(0.f, 0.f);
    for (int i = 0; i < fHeight; ++i) // Arriba-abajo
    {
        for (int j = 0; j < fWidth; ++j) // Izquierda-derecha
        {
            // Chequeamos si el pixel actual esta dentro del circulo
            oDistancePixelCircle = Vec2(j + fPosX, i + fPosY) - circlePos;
            if (oDistancePixelCircle.length() < circleRadius)
            {
                // Calculamos la posicion relativa del pixel actual respecto al sprite de pixeles
                iPixelPosX = j + fPosX - pixelsPos.GetX();
                iPixelPosY = i + fPosY - pixelsPos.GetY();
                // Calculamos el index del alpha a partir de la posicion relativa
                iIndexPixel = (iPixelPosY * pixelsSize.GetX() + iPixelPosX) * 4 + 3;
                if (pixels[iIndexPixel] != 0)
                {
                    return true;
                    //lgfx_setcolor(0, 255, 0, 255);
                    //lgfx_drawpoint(j, i);
                }
                //else
                //{
                //	lgfx_setcolor(255, 0, 0, 255);
                //	lgfx_drawpoint(j, i);
                //}
            }

        }
    }

    return false;
}

bool Collider::checkPixelsPixels(const Vec2& pixelsPos1, const Vec2& pixelsSize1, const uint8_t* pixels1, const Vec2& pixelsPos2, const Vec2& pixelsSize2, const uint8_t* pixels2) const
{
    // Return false si los rectangulos no solapan
    if (!checkRectRect(pixelsPos1, pixelsSize1, pixelsPos2, pixelsSize2))
    {
        return false;
    }

    // Rectangulo que solapa
    float fPosX = (pixelsPos1.GetX() < pixelsPos2.GetX()) ? pixelsPos2.GetX() : pixelsPos1.GetX();
    float fWidth = std::fminf(pixelsPos1.GetX() + pixelsSize1.GetX(), pixelsPos2.GetX() + pixelsSize2.GetX()) - fPosX;
    float fPosY = (pixelsPos1.GetY() < pixelsPos2.GetY()) ? pixelsPos2.GetY() : pixelsPos1.GetY();
    float fHeight = std::fminf(pixelsPos1.GetY() + pixelsSize1.GetY(), pixelsPos2.GetY() + pixelsSize2.GetY()) - fPosY;
    //lgfx_setcolor(255, 0, 0, 255);
    //lgfx_drawrect(fPosX, fPosY, fWidth, fHeight);

    // Iteramos por el rectangulo que solapa
    int iPixel1PosX, iPixel2PosX = 0;
    int iPixel1PosY, iPixel2PosY = 0;
    int iIndexPixel1, iIndexPixel2 = 0;
    for (int i = 0; i < fHeight; ++i) // Arriba-abajo
    {
        for (int j = 0; j < fWidth; ++j) // Izquierda-derecha
        {
            // == PIXEL 1 ==
            // Calculamos la posicion relativa del pixel actual respecto al sprite de pixeles
            iPixel1PosX = j + fPosX - pixelsPos1.GetX();
            iPixel1PosY = i + fPosY - pixelsPos1.GetY();
            // Calculamos el index del alpha a partir de la posicion relativa
            iIndexPixel1 = (iPixel1PosY * pixelsSize1.GetX() + iPixel1PosX) * 4 + 3;

            // == PIXEL 2 ==
            // Calculamos la posicion relativa del pixel actual respecto al sprite de pixeles
            iPixel2PosX = j + fPosX - pixelsPos2.GetX();
            iPixel2PosY = i + fPosY - pixelsPos2.GetY();
            // Calculamos el index del alpha a partir de la posicion relativa
            iIndexPixel2 = (iPixel2PosY * pixelsSize2.GetX() + iPixel2PosX) * 4 + 3;

            if (pixels1[iIndexPixel1] != 0 && pixels2[iIndexPixel2] != 0)
            {
                return true;
                //lgfx_setcolor(0, 255, 0, 255);
                //lgfx_drawpoint(j, i);
            }
            //else
            //{
            //	lgfx_setcolor(255, 0, 0, 255);
            //	lgfx_drawpoint(j, i);
            //}
        }
    }

    return false;
}

bool Collider::checkPixelsRect(const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels, const Vec2& rectPos, const Vec2& rectSize) const
{
    // Return false si los rectangulos no solapan
    if (!checkRectRect(pixelsPos, pixelsSize, rectPos, rectSize))
    {
        return false;
    }

    // Rectangulo que solapa
    float fPosX = (pixelsPos.GetX() < rectPos.GetX()) ? rectPos.GetX() : pixelsPos.GetX();
    float fWidth = std::fminf(pixelsPos.GetX() + pixelsSize.GetX(), rectPos.GetX() + rectSize.GetX()) - fPosX;
    float fPosY = (pixelsPos.GetY() < rectPos.GetY()) ? rectPos.GetY() : pixelsPos.GetY();
    float fHeight = std::fminf(pixelsPos.GetY() + pixelsSize.GetY(), rectPos.GetY() + rectSize.GetY()) - fPosY;
    //printf("Pixel: %f, %f | %f, %f\n", pixelsPos.GetX(), pixelsPos.GetY(), pixelsSize.GetX(), pixelsSize.GetY());
    //printf("Rect: %f, %f | %f, %f\n", rectPos.GetX(), rectPos.GetY(), rectSize.GetX(), rectSize.GetY());
    //printf("Rect que solapa: %f, %f | %f, %f\n", fPosX, fPosY, fWidth, fHeight);

    // Iteramos por el rectangulo que solapa
    int iPixelPosX = 0;
    int iPixelPosY = 0;
    int iIndexPixel = 0;
    for (int i = 0; i < fHeight; ++i) // Arriba-abajo
    {
        for (int j = 0; j < fWidth; ++j) // Izquierda-derecha
        {
            // Calculamos la posicion relativa del pixel actual respecto al sprite de pixeles
            iPixelPosX = j + fPosX - pixelsPos.GetX();
            iPixelPosY = i + fPosY - pixelsPos.GetY();
            // Calculamos el index del alpha a partir de la posicion relativa
            iIndexPixel = (iPixelPosY * pixelsSize.GetX() + iPixelPosX) * 4 + 3;
            if (pixels[iIndexPixel] != 0)
            {
                return true;
                //lgfx_setcolor(0, 255, 0, 255);
                //lgfx_drawpoint(j, i);
            }
            //else
            //{
            //	lgfx_setcolor(255, 0, 0, 255);
            //	lgfx_drawpoint(j, i);
            //}
        }
    }

    return false;
}

*/
