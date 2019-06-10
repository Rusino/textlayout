// Potential users:
// 1. Text editor (lot's of measurement and flexible styling)
// 2. Simple text with basic styling (API as simple as possible)
// 3. Generated code (API does not have to be fancy, but rather cover all the
// cases)
// Would JSON format be good for javascript calling c++?
namespace text {
namespace layout {
void try1() {
  // Styles defined by range (have to count and track ranges)
  RangeTextLayout layout("World domination is such an ugly phrase - I prefer "
                         "to call it world optimisation");
  layout.setEllipsis("\u2026");
  layout.setFontFamilies({"Roboto"});
  layout.addRange(0, 5)
      .setFontFamilies({"Google Sans", "Color Emoji"})
      .setFontSize(50.0f);
  layout.addRange(6, 16)
      .setFontFamilies({"Monospace", "Color Emoji"})
      .setFontStyle(SkFontStyle::BoldItalic());
  layout.addRange(0, 5)
      .addForeground(SK_ColorYELLOW)
      .addDecoration(TextDecoration::kUnderline, TextDecorationStyle::kDouble,
                     SK_ColorLTGRAY, 1.0f);
  layout.addRange(6, 16)
      .addBackground(SK_ColorGRAY)
      .addShadow(TextShadow(SK_ColorBLUE, SkPoint(5, 5), 2));
  layout.measure();              // optional step
  layout.paint(0, 0, 100.0f, 3); // (lazy) format, (lazy) style and paint

  // Slightly better:
  layout [0:5]
      .setFontFamilies({"Google Sans", "Color Emoji"})
      .setFontSize(50.0f);
  layout [6:16]
      .setFontFamilies({"Monospace", "Color Emoji"})
      .setFontStyle(SkFontStyle::BoldItalic());
  layout [0:5]
      .addForeground(SK_ColorYELLOW) // color ->paint
      .addShadow(SK_ColorBLUE + 2)   // color ->shadow + int
      .addDecoration(TextDecoration::kUnderline)
      .addDecorationStyle(TextDecorationStyle::kDouble)
      .addDecorationColor(SK_ColorLTGRAY)
      .addDecorationMultiplier(2.0f);
  layout [6:16]
      .addBackground(SK_ColorGRAY)
      .addShadow(SK_ColorBLUE + SkPoint(5, 5) + 2))
      .addDecoration(TextDecoration::kUnderline + 2.0f);

  // Slightly shorter (could be much shorter!):
  auto style0 = TextStyle().addFontSize(50);
  auto style1 = style0
                    .addForeground(SK_ColorYELLOW) // color ->paint
                    .addShadow(SK_ColorBLUE + 2)   // color ->shadow + int
                    .addDecoration(TextDecoration::kUnderline)
                    .addDecorationStyle(TextDecorationStyle::kDouble)
                    .addDecorationColor(SK_ColorLTGRAY)
                    .addDecorationMultiplier(2.0f)
                    .setFontFamilies({"Google Sans", "Color Emoji"});
  auto style2 = style0.addBackground(SK_ColorGRAY)
                    .addShadow(SK_ColorBLUE + SkPoint(5, 5) + 2)
                    .addDecoration(TextDecoration::kUnderline + 2.0f)
                    .setFontFamilies({"Monospace", "Color Emoji"});
  // Styles can intersect; the last one wins
  layout.text(0 : 5).setStyle(style1);
  layout.text(6 : 16).setStyle(style2);
}

void try2() {
  // Styles defined in the text (only good for limited marks)
  // Text with markup
  // One font or one list of fonts
  // <b>old <i>talic <u>nderline <s>trike <o>verline
  MarkupTextLayout layout({"Roboto"},
                          "<b><i>World</b></i> domination <u>is such an ugly "
                          "phrase</u> - I prefer to call it "
                          "world optimisation");
  layout.measure();              // optional step
  layout.paint(0, 0, 100.0f, 3); // format, style and paint

  // The shortest
  MarkupTextLayout({"Roboto"},
                   "<b><i>World</b></i> domination <u>is such an ugly "
                   "phrase</u> - I prefer to call it "
                   "world optimisation")
      .paint(0, 0, 100.0f, 3);
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
      .addDecoration(TextDecoration::kUnderline, TextDecorationStyle::kDouble,
                     SK_ColorLTGRAY, 1.0f);
  layout.addText(" is such an ugly phrase")
      .setFontFamilies({"Monospace", "Color Emoji"})
      .setFontStyle(SkFontStyle::BoldItalic());
  layout.addText(" - I prefer to call it world optimisation")
      .addBackground(SK_ColorGRAY)
      .addShadow(TextShadow(SK_ColorBLUE, SkPoint(5, 5), 2));
  layout.measure();
  layout.paint(0, 0, 100.0f /*width*/, 3 /*maxLines*/);

  auto style0 = TextStyle().addFontSize(50);
  auto style1 = style0
                    .addForeground(SK_ColorYELLOW) // color ->paint
                    .addShadow(SK_ColorBLUE + 2)   // color ->shadow + int
                    .addDecoration(TextDecoration::kUnderline)
                    .addDecorationStyle(TextDecorationStyle::kDouble)
                    .addDecorationColor(SK_ColorLTGRAY)
                    .addDecorationMultiplier(2.0f)
                    .setFontFamilies({"Google Sans", "Color Emoji"});
  auto style2 = style0.addBackground(SK_ColorGRAY)
                    .addShadow(SK_ColorBLUE + SkPoint(5, 5) + 2)
                    .addDecoration(TextDecoration::kUnderline + 2.0f)
                    .setFontFamilies({"Monospace", "Color Emoji"});

  layout.addText("World domination").setStyle(style1);
  layout.addText(" is such an ugly phrase").setStyle(style2);
  layout.addText(" - I prefer to call it world optimisation").setStyle(style0);

  layout.addText(style1, "World domination");
  layout.addText(style2, " is such an ugly phrase");
  layout.addText(style0, " - I prefer to call it world optimisation");

  layout << style1 << "World domination";
  layout << style2 << " is such an ugly phrase";
  layout << style0 << " - I prefer to call it world optimisation";
}

void try4() {
  // Simplest layout possible
  SimpleLayout("...", {"Roboto"}).paint(100, 3, 0, 0);

  SimpleLayout layout("...", {"Roboto"});
  layout.paint(100, 3, 0, 0); // measure/style/draw

  SimpleLayout layout("...", {"Roboto"});
  layout.measure(100, 3);
  layout.style(...);
  layout.draw(0, 0);
}

void try5() {
  // Styles defined by range in order of appearance (complex initialization
  // list)
  RangeLayout layout("World domination is such an ugly phrase - I prefer to "
                     "call it world optimisation");
  layout.style({
      {0, 6, {SK_ColorRED, SK_ColorWHITE, {"Roboto", "Emoji"}}},
      {7, 16, {SkFontStyle::BoldItalic(), {"Monospace"}}},
  });
  layout.measure();              // optional step
  layout.paint(0, 0, 100.0f, 3); // format, style and paint
}

void try6() {
  // Styles defined by words (ICU word breaking is not obvious for punctuation)
  // Word breaking by ICU
  WordLayout layout("World domination is such an ugly phrase - I prefer to "
                    "call it world optimisation");
  layout.styleWord(1, {SK_ColorRED, SK_ColorWHITE, {"Roboto", "Emoji"}});
  layout.styleWords(2, 5, {SkFontStyle::BoldItalic(), {"Monospace"}});
  layout.measure();              // optional step
  layout.paint(0, 0, 100.0f, 3); // format, style and paint
}

void try7() {
  // Experiments
  /*
   * "{1}" "World" "{2}" " " "{3}" "domination" "{4}" " " "is such an ugly
   * phrase - I prefer to call it world optimisation"
   * "{1}World{2} {3}domination{4} is such an ugly phrase - I prefer to call it
   * world optimisation"
   *
   * "World domination is such an ugly phrase - I prefer to call it world
   * optimisation" "1    23         45                     6 7"
   */

  // Text is duplicated partually and needs to be updated in two places
  WordLayout layout("World domination is such an ugly phrase - I prefer to "
                    "call it World optimisation");
  layout.first("World")
      .setFontFamilies({"Google Sans", "Color Emoji"})
      .setFontSize(50.0f);
  layout.last("World")
      .setFontFamilies({"Monospace", "Color Emoji"})
      .setFontStyle(SkFontStyle::BoldItalic());
  layout.select("optim")
      .addForeground(SK_ColorYELLOW)
      .addDecoration(TextDecoration::kUnderline, TextDecorationStyle::kDouble,
                     SK_ColorLTGRAY, 1.0f);
  layout.range(" I prefer ", "optimisation")
      .addBackground(SK_ColorGRAY)
      .addShadow(TextShadow(SK_ColorBLUE, SkPoint(5, 5), 2));
  layout.measure();              // optional step
  layout.paint(0, 0, 100.0f, 3); // format, style and paint

  // More manageable:
  auto style0 = TextStyle().addFontSize(50);
  auto style1 = style0
                    .addForeground(SK_ColorYELLOW) // color ->paint
                    .addShadow(SK_ColorBLUE + 2)   // color ->shadow + int
                    .addDecoration(TextDecoration::kUnderline)
                    .addDecorationStyle(TextDecorationStyle::kDouble)
                    .addDecorationColor(SK_ColorLTGRAY)
                    .addDecorationMultiplier(2.0f)
                    .setFontFamilies({"Google Sans", "Color Emoji"});
  auto style2 = style0.addBackground(SK_ColorGRAY)
                    .addShadow(SK_ColorBLUE + SkPoint(5, 5) + 2)
                    .addDecoration(TextDecoration::kUnderline + 2.0f)
                    .setFontFamilies({"Monospace", "Color Emoji"});

  layout << style1 << first("World");
  layout << style2 << last("World");
  layout << style1 << select("optim");
  layout << style2 << range(" I prefer ", "optimisation");
}

void try8() {
  // Text is broken down and cannot be seen at once
  TextLayout layout();
  layout.fonts({"1", SkFont("Roboto", 16, SkFontStyle::kItalic_Slant, "en_US",
                            TextDirection::kLtr)});
  layout.shadows("1", TextShadow());
  layout.decorations("1", TextDecoration());
  layout << "{b}"
         << "World"
         << "{/b}"
         << "{f:1}"
         << "domination"
         << "{/f}"
         << " is such an ugly phrase - "
         << "{shadow:1}"
         << "I prefer to "
         << "{/shadow}"
         << "{decoration:1}"
         << "call it World optimisation";
}

void try9() {
  TextLayout layout("World domination is such an ugly phrase - I prefer to "
                    "call it World optimisation");
  layout.text(0, 6)
      .setFontFamilies({"Google Sans", "Color Emoji"})
      .setFontSize(50.0f);
  layout.text(7, 16)
      .setFontFamilies({"Monospace", "Color Emoji"})
      .setFontStyle(SkFontStyle::BoldItalic());
}

void try10() {
  // JSON-like style (too many curly braces)
  TextLayout layout("World domination is such an ugly phrase - I prefer to "
                    "call it World optimisation");

  layout.text(0, 20) << {{"FontFamilies", {"Roboto", "Emoji", "Monospace"}},
                         {"FontSize", 50f}};
  layout.text(0, 10) << {
      {"FontStyle", SkFontStyle::BoldItalic()},
      {"Shadows" : {{"Shadow" : {"Color", SK_ColorBlack, "Blur" : 5f}}}},
  };
  layout.text(10, 20) << {
      {"FontStyle", SkFontStyle::Bold()},
      {"Shadows" : {{"Shadow" : {"Color", SK_ColorGray, "Blur" : 5f}}}},
  };

  auto style0 = {{"FontFamilies", {"Roboto", "Emoji", "Monospace"}},
                 {"FontSize", 50f}};
  auto style1 = {
      {"FontStyle", SkFontStyle::BoldItalic()},
      {"Shadows" : {{"Shadow" : {"Color", SK_ColorBlack, "Blur" : 5f}}}},
  };
  auto style2 = {
      {"FontStyle", SkFontStyle::Bold()},
      {"Shadows" : {{"Shadow" : {"Color", SK_ColorGray, "Blur" : 5f}}}},
  };
  layout.text(0, 20) << style0;
  layout.text(0, 10) << style1;
  layout.text(10, 20) << style2;
};

} // namespace layout
} // namespace text
