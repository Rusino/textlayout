// Potential users:
// 1. Text editor (lot's of measurement and flexible styling)
// 2. Simple text with basic styling (API as simple as possible)
// 3. Generated code (API does not have to be fancy, but rather cover all the cases)
namespace text {
namespace layout {
void try1() {
    // Styles defined by range (have to count and track ranges)
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
    layout.paint(0, 0, 100.0f, 3);  // (lazy) format, (lazy) style and paint
}

void try2() {
    // Styles defined in the text (only good for limited marks)
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
    // Styles defined by text (text is lost somewhere)
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
    // Styles defined by range in order of appearance (complex initialization list)
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
    // Styles defined by words (ICU word breaking is not obvious for punctuation)
    // Word breaking by ICU
    WordLayout layout(
            "World domination is such an ugly phrase - I prefer to call it world optimisation");
    layout.styleWord(1, {SK_ColorRED, SK_ColorWHITE, {"Roboto", "Emoji"}});
    layout.styleWords(2, 5, {SkFontStyle::BoldItalic(), {"Monospace"}});
    layout.measure();               // optional step
    layout.paint(0, 0, 100.0f, 3);  // format, style and paint
}

void try7() {
    // Experiments
    /*
     * "{1}" "World" "{2}" " " "{3}" "domination" "{4}" " " "is such an ugly phrase - I prefer to call it world optimisation"
     * "{1}World{2} {3}domination{4} is such an ugly phrase - I prefer to call it world optimisation"
     *
     *   "World domination is such an ugly phrase - I prefer to call it world optimisation"
     *   "1    23         45                     6                                        "
     */
    WordLayout layout(
        "World domination is such an ugly phrase - I prefer to call it world optimisation");
    layout.select("World").setFontFamilies({"Google Sans", "Color Emoji"}).setFontSize(50.0f);
    layout.select("World", 2)
        .setFontFamilies({"Monospace", "Color Emoji"})
        .setFontStyle(SkFontStyle::BoldItalic());
    layout.select("ugly phrase")
        .addForeground(SK_ColorYELLOW)
        .addDecoration(
            TextDecoration::kUnderline, TextDecorationStyle::kDouble, SK_ColorLTGRAY, 1.0f);
    layout.range(" I prefer ")
        .addBackground(SK_ColorGRAY)
        .addShadow(TextShadow(SK_ColorBLUE, SkPoint(5, 5), 2));
    layout.measure();               // optional step
    layout.paint(0, 0, 100.0f, 3);  // format, style and paint
}

}  // namespace layout
}  // namespace text
