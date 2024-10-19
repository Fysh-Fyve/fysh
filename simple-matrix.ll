; ModuleID = 'fysh'
source_filename = "simple-matrix.fysh"

define i32 @set_pixel(i32 %row, i32 %col) {
entry:
  %andtmp = shl i32 %row, 3
  %shltmp = and i32 %andtmp, 56
  %andtmp1 = and i32 %col, 7
  %ortmp = or i32 %andtmp1, 128
  %ortmp2 = or i32 %ortmp, %shltmp
  call void @fysh_gpio_write_all(i32 %ortmp2)
  ret i32 %ortmp2
}

declare void @fysh_gpio_write_all(i32)

define i32 @draw_fysh(i32 %dy, i32 %dx) {
entry:
  %0 = call i32 @set_pixel(i32 %dy, i32 %dx)
  ; More code ... ;
  %addtmp2 = add i32 %dy, 2
  %addtmp3 = add i32 %dx, 3
  %1 = call i32 @set_pixel(i32 %addtmp2, i32 %addtmp3)
  ret i32 %1
}

define i32 @main() {
entry:
  br label %loop_cond

loop_cond:
  %0 = call i32 @draw_fysh(i32 1, i32 0)
  ; More code ... ;
  %1 = call i32 @draw_fysh(i32 1, i32 7)
  br label %loop_cond
}
