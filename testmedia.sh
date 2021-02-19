keys="WASD";
for ((i=0;i<${#keys};i++));
do 
   pango-view --font="sans mono" -qo image.svg --text "${keys:$i:1}";
   inkscape -w 128 -h 128 -b "#ffffffff" image.svg -o "media/${keys:$i:1}.png";
done;
pango-view --font="sans mono" -qo image.svg --text "None";
inkscape -w 128 -h 128 -b "#ffffffff" image.svg -o "media/Default.png";
pango-view --font="sans mono" -qo image.svg --text "Character";
inkscape -w 128 -h 128 -b "#ffffffff" image.svg -o "media/character.png";
rm image.svg