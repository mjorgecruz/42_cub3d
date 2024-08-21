#!/bin/bash

for map in \
  broken_xpm.cub filetype_wrong.buc map_too_small.cub textures_forbidden.cub wall_hole_east.cub wrong14.cub wrong22.cub wrong30.cub wrong39.cub xpm_wrong_size.cub \
  color_invalid_rgb.cub invalid_4_color.cub player_multiple.cub textures_invalid.cub wall_hole_north.cub wrong15.cub wrong23.cub wrong31.cub wrong3.cub \
  color_missing_ceiling_rgb.cub invalid_map.ber player_none.cub textures_missing.cub wall_hole_south.cub wrong16.cub wrong24.cub wrong32.cub wrong4.cub \
  color_missing.cub invalid_map_char.cub player_on_edge.cub textures_multiple_words.cub wall_hole_west.cub wrong17.cub wrong25.cub wrong33.cub wrong5.cub \
  color_missing_floor_rgb.cub invalid_map.cub subject_map.cub textures_none.cub wall_none.cub wrong18.cub wrong26.cub wrong34.cub wrong6.cub \
  color_none.cub map_first.cub test_map_hole.cub textures_not_xpm.cub wrong10.cub wrong19.cub wrong27.cub wrong35.cub wrong7.cub \
  duplicated_setting.cub map_middle.cub textures_dir2.cub textures_value_missing.cub wrong11.cub wrong1.cub wrong28.cub wrong36.cub wrong8.cub \
  empty.cub map_missing.cub textures_dir.cub triangle_open.cub wrong12.cub wrong20.cub wrong29.cub wrong37.cub wrong9.cub wrong_setting.cub;
do
  valgrind ./cub3d_bonus maps/invalid/$map 
done

