SET(SOURCES screens/ui_Screen1.c
    screens/ui_Screen2.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    images/ui_img_neutral_chess_king_svg_png.c
    fonts/ui_font_ChessSymbols.c
    fonts/ui_font_NeutralKing.c)

add_library(ui ${SOURCES})
