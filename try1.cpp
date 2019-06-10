// Potential users:
// 1. Text editor (lot's of measurement and flexible styling)
// 2. Simple text with basic styling (API as simple as possible)
// 3. Generated code (API does not have to be fancy, but rather cover all the cases)
namespace text {
namespace layout {
void try1() {
    // Add random ranges with styles
    RangeTextLayout layout(
            "World domination is such an ugly phrase - I prefer to call it world optimisation");
    layout.setEllipsis("\u2026");
    layout.setFontFamilies({"Roboto"});
    layout.addRange(0, 5).setFontFamilies({"Google Sans", "Color Emoji"}).setFontSize(50.0f);
    layout.addRange(6, 16)
            .setFontFamilies({"Monospace", "Color Emoji"})
            .setFontStyle(SkFontStyle::BoldItalic());
    layout.addRange(0, 5)
            .addForeground(SK_ColorYELLOW)
            .addDecoration(
                    TextDecoration::kUnderline, TextDecorationStyle::kDouble, SK_ColorLTGRAY, 1.0f);
    layout.addRange(6, 16)
            .addBackground(SK_ColorGRAY)
            .addShadow(TextShadow(SK_ColorBLUE, SkPoint(5, 5), 2));
    layout.measure();               // optional step
    layout.paint(0, 0, 100.0f, 3);  // format, style and paint
}

void try2() {
    // Text with markup
    // One font or one list of fonts
    // <b>old <i>talic <u>nderline <s>trike <o>verline
    MarkupTextLayout layout(
            {"Roboto"},
            "<b><i>World</b></i> domination <u>is such an ugly phrase</u> - I prefer to call it "
            "world optimisation");
    layout.measure();               // optional step
    layout.paint(0, 0, 100.0f, 3);  // format, style and paint
}

void try3() {
    // Add text with styles
    StyleLayout layout;
    layout.setEllipsis("\u2026");
    layout.setFontFamilies({"Roboto"});
    layout.addText("World domination")
            .setFontFamilies({"Google Sans", "Color Emoji"})
            .setFontSize(50.0f)
            .addForeground(SK_ColorYELLOW)
            .addDecoration(
                    TextDecoration::kUnderline, TextDecorationStyle::kDouble, SK_ColorLTGRAY, 1.0f);
    layout.addText(" is such an ugly phrase")
            .setFontFamilies({"Monospace", "Color Emoji"})
            .setFontStyle(SkFontStyle::BoldItalic());
    layout.addText(" - I prefer to call it world optimisation")
            .addBackground(SK_ColorGRAY)
            .addShadow(TextShadow(SK_ColorBLUE, SkPoint(5, 5), 2));
    layout.measure();
    layout.paint(0, 0, 100.0f /*width*/, 3 /*maxLines*/);
}

void try4() {
    // Simplest layout possible
    SimpleLayout::paint("...", {"Roboto"}, 100, 3, 0, 0);

    SimpleLayout layout("...", {"Roboto"});
    layout.paint(100, 3, 0, 0);  // measure/style/draw

    SimpleLayout layout("...", {"Roboto"});
    layout.measure(100, 3);
    layout.style(...);
    layout.draw(0, 0);
}

void try5() {
    // Styles by range in order of appearance
    RangeLayout layout(
            "World domination is such an ugly phrase - I prefer to call it world optimisation");
    layout.style({
            {0, 6, {SK_ColorRED, SK_ColorWHITE, {"Roboto", "Emoji"}}},
            {7, 16, {SkFontStyle::BoldItalic(), {"Monospace"}}},
    });
    layout.measure();               // optional step
    layout.paint(0, 0, 100.0f, 3);  // format, style and paint
}

void try6() {
    // Word breaking by ICU
    WordLayout layout(
            "World domination is such an ugly phrase - I prefer to call it world optimisation");
    layout.style(1, 2, {SK_ColorRED, SK_ColorWHITE, {"Roboto", "Emoji"}});
    layout.style(2, 5, {SkFontStyle::BoldItalic(), {"Monospace"}});
    layout.measure();               // optional step
    layout.paint(0, 0, 100.0f, 3);  // format, style and paint
}

}  // namespace layout
}  // namespace text
