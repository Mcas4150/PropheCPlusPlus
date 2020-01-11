//
//struct GroupLookAndFeel    : public LookAndFeel_V4
//{
//    
//    void drawGroupComponentOutline (Graphics& g, int width, int height,
//                                    const String& text, const Justification& position,
//                                    GroupComponent& group)
//    {
//        const float textH = 12.0f;
//        const float indent = 3.0f;
//        const float textEdgeGap = 4.0f;
//        auto cs = 5.0f;
//        
//        Font f (textH);
//        
//        Path p;
//        auto x = indent;
//        auto y = f.getAscent() - 3.0f;
//        auto w = jmax (0.0f, width - x * 2.0f);
//        auto h = jmax (0.0f, height - y  - indent);
//        cs = jmin (cs, w * 0.5f, h * 0.5f);
//        auto cs2 = 2.0f * cs;
//        
//        auto textW = text.isEmpty() ? 0 : jlimit (0.0f, jmax (0.0f, w - cs2 - textEdgeGap * 2), f.getStringWidth (text) + textEdgeGap * 2.0f);
//        auto textX = cs + textEdgeGap;
//        
//        if (position.testFlags (Justification::horizontallyCentred))
//            textX = cs + (w - cs2 - textW) * 0.5f;
//        else if (position.testFlags (Justification::right))
//            textX = w - cs - textW - textEdgeGap;
//        
//        p.startNewSubPath (x + textX + textW, y);
//        p.lineTo (x + w - cs, y);
//        
//        p.addArc (x + w - cs2, y, cs2, cs2, 0, MathConstants<float>::halfPi);
//        p.lineTo (x + w, y + h - cs);
//        
//        p.addArc (x + w - cs2, y + h - cs2, cs2, cs2, MathConstants<float>::halfPi, MathConstants<float>::pi);
//        p.lineTo (x + cs, y + h);
//        
//        p.addArc (x, y + h - cs2, cs2, cs2, MathConstants<float>::pi, MathConstants<float>::pi * 1.5f);
//        p.lineTo (x, y + cs);
//        
//        p.addArc (x, y, cs2, cs2, MathConstants<float>::pi * 1.5f, MathConstants<float>::twoPi);
//        p.lineTo (x + textX, y);
//        
//        auto alpha = group.isEnabled() ? 1.0f : 0.5f;
//        
//        g.setColour (Colours::silver);
//        
//        g.strokePath (p, PathStrokeType (2.0f));
//        
//        g.setColour (Colours::whitesmoke);
//        g.setFont (f);
//        g.drawText (text,
//                    roundToInt (x + textX), 0,
//                    roundToInt (textW),
//                    roundToInt (textH),
//                    Justification::centred, true);
//    }
//    
//    
//    
//    
//};
