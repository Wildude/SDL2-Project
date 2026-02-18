#include <uibutton.hpp>
// UIbutton implementation

UIbutton::UIbutton(UIButtonType type)
    : buttontype(type), offset(0) {
    // Constructor implementation
}
// sets the position of the button
void UIbutton::setPos(int x, int y) {
    box.content.x = x;
    box.content.y = y;
}
// gets the font of the button
FONT* UIbutton::getFont() {
    // Placeholder implementation, return a default font
    return nullptr;
}
// updates the button (handles hover, click states)
void UIbutton::update(InputManager& input) {
    // Call base class update to handle state changes
    UIelement::update(input);
    // Additional button-specific update logic can go here
}
// renders the button
void UIbutton::render(SDL_Renderer* rend, int drawtype) {
    UIelement::render(rend, drawtype);
    SDL_Rect contentrect = {
        box.content.x + box.margin + box.border + box.padding,
        box.content.y + box.margin + box.border + box.padding,
        box.content.w,
        box.content.h
    };
    switch (buttontype)
    {
        case UIBT_DEFAULT:
            // Render default button style
            SDL_SetRenderDrawColor(rend, bg.r, bg.g, bg.b, bg.a);
            SDL_RenderDrawRect(rend, &contentrect);
            if(isclick) {
                // Render offset effect (e.g., pressed state)
                SDL_SetRenderDrawColor(rend, fg.r, fg.g, fg.b, fg.a);
                contentrect.x += offset;
                contentrect.y += offset;
                contentrect.w -= offset * 2;
                contentrect.h -= offset * 2;
                SDL_RenderDrawRect(rend, &contentrect);
                
            }
            break;
        case UIBT_INCREMENT:
            // Render increment button style
            {
                // draw a triangle (trigon) inside contentrect with a border thickness
                const int thickness = 6; // desired border thickness in pixels

                // outer triangle vertices (top-center, bottom-left, bottom-right)
                Sint16 x1 = contentrect.x + contentrect.w / 2;
                Sint16 y1 = contentrect.y + contentrect.h / 6;
                Sint16 x2 = contentrect.x + contentrect.w / 6;
                Sint16 y2 = contentrect.y + contentrect.h * 5 / 6;
                Sint16 x3 = contentrect.x + contentrect.w * 5 / 6;
                Sint16 y3 = contentrect.y + contentrect.h * 5 / 6;

                // draw filled outer triangle (use foreground color)
                filledTrigonRGBA(rend, x1, y1, x2, y2, x3, y3, fg.r, fg.g, fg.b, fg.a);

                // compute centroid
                double cx = (x1 + x2 + x3) / 3.0;
                double cy = (y1 + y2 + y3) / 3.0;

                // helper to inset a vertex toward the centroid by 'thickness' pixels
                auto inset_vertex = [&](double vx, double vy, Sint16 &outx, Sint16 &outy) {
                    double dx = vx - cx;
                    double dy = vy - cy;
                    double dist = sqrt(dx * dx + dy * dy);
                    if (dist > 1e-6) {
                        double factor = (dist - thickness) / dist;
                        if (factor < 0.0) factor = 0.0;
                        outx = (Sint16)round(cx + dx * factor);
                        outy = (Sint16)round(cy + dy * factor);
                    } else {
                        outx = (Sint16)round(cx);
                        outy = (Sint16)round(cy);
                    }
                };

                // inner (eroded) triangle to carve out the center, creating a border of 'thickness'
                Sint16 ix1, iy1, ix2, iy2, ix3, iy3;
                inset_vertex(x1, y1, ix1, iy1);
                inset_vertex(x2, y2, ix2, iy2);
                inset_vertex(x3, y3, ix3, iy3);

                // fill the inner triangle with background color to leave a border of the given thickness
                filledTrigonRGBA(rend, ix1, iy1, ix2, iy2, ix3, iy3, bg.r, bg.g, bg.b, bg.a);
            }
            break;
        case UIBT_DECREMENT:
            // Render decrement button style
            break;
    }
    // Render the button background and text based on its state
    // Placeholder implementation for rendering
}
// destructor for UIbutton
UIbutton::~UIbutton() {
    // Destructor implementation
}
