update_compile_order -fileset sources_1
update_compile_order -fileset sim_1
launch_runs impl_1 -to_step write_bitstream -jobs 4
wait_on_run impl_1
if {[get_property PROGRESS [get_runs impl_1]] != "100%"} {
   error "ERROR: impl_1 failed"
}
