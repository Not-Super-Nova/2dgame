pango-view --font="sans mono" -qo image.svg --text "Character";
inkscape -w 128 -h 128 -b "#ffffffff" image.svg -o "media/character.png";
rm image.svg
