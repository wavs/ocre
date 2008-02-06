val surf_to_matrix :
  Sdlvideo.surface ->
  (int32, Bigarray.int32_elt, Bigarray.c_layout) Bigarray.Array2.t
val matrix_to_surf : (int32, 'a, 'b) Bigarray.Array2.t -> Sdlvideo.surface
