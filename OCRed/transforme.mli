val surf_to_matrix :
  Sdlvideo.surface -> (int32,
                       Bigarray.int32_elt,
                       Bigarray.c_layout) Bigarray.Array2.t

val matrix_to_surf : ((int32, 'a, 'b) Bigarray.Array2.t ->
                        Sdlvideo.surface)
(*le probleme viendrait de l'absence de typage*)
val bigarray2 : int -> int -> (int32,
                               Bigarray.int32_elt,
                               Bigarray.c_layout) Bigarray.Array2.t
val shift_pixel :    ('a, 'b, 'c) Bigarray.Array2.t ->
  ('a, 'd, 'e) Bigarray.Array2.t ->
  int ->
  int ->
  int ->
  int ->
  unit
