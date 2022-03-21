// void Sprite::setCollisionType(CollisionType type)
// {
//     if (m_pCollider)
//     {
//         delete m_pCollider;
//         m_pCollider = nullptr;
//     }
//     m_CollisionType = type;
// 
//     if (m_CollisionType == Sprite::COLLISION_CIRCLE)
//     {
//         // oPos = centro del sprite
//         Vec2 oPosTopLeft = m_Position - Vec2(m_pTexture->width * m_Pivot.GetX(), m_pTexture->height * m_Pivot.GetY());
//         Vec2 oPos = oPosTopLeft + Vec2(m_pTexture->width / 2, m_pTexture->height / 2);
// 
//         // fRadius = mitad del ancho o el alto (el mayor de los dos)
//         float fRadius = (m_pTexture->width > m_pTexture->height) ? m_pTexture->width / 2 : m_pTexture->height / 2;
//         fRadius *= m_Scale.GetX(); // O 'y', da igual porque siempre es un circulo
// 
//         m_pCollider = new CircleCollider(oPos, fRadius);
//     }
//     else if (m_CollisionType == Sprite::COLLISION_RECT)
//     {
//         // oSize = tamanio textura * escala
//         Vec2 oSize = Vec2(m_pTexture->width, m_pTexture->height) * m_Scale;
//         // oPos = posicion del sprite 'quitando' el pivote
//         Vec2 oPos = m_Position - Vec2(oSize.GetX() * m_Pivot.GetX(), oSize.GetY() * m_Pivot.GetY());
// 
//         m_pCollider = new RectCollider(oPos, oSize);
//     }
//     else if (m_CollisionType == Sprite::COLLISION_PIXELS)
//     {
//         // oSize = tamanio textura
//         Vec2 oSize = Vec2(m_pTexture->width, m_pTexture->height) * m_Scale;
//         // oPos = posicion del sprite 'quitando' el pivote
//         Vec2 oPos = m_Position - Vec2(oSize.GetX() * m_Pivot.GetX(), oSize.GetY() * m_Pivot.GetY());
// 
//         // getpixels
//         m_pPixelsBuffer = new unsigned char[m_pTexture->width * m_pTexture->height * 4];
//         ltex_getpixels(m_pTexture, m_pPixelsBuffer);
// 
//         m_pCollider = new PixelsCollider(oPos, oSize, m_pPixelsBuffer);
//     }
// }