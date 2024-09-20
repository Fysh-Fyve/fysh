set script_path [ file dirname [ file normalize [ info script ] ] ]
set project_directory $script_path/proj
set bitstream $project_directory/fysh-fyve.runs/impl_1/topmodule.bit

open_hw_manager
connect_hw_server -allow_non_jtag
open_hw_target
set_property PROGRAM.FILE $bitstream [get_hw_devices xc7z010_1]
current_hw_device [get_hw_devices xc7z010_1]
refresh_hw_device -update_hw_probes false [lindex [get_hw_devices xc7z010_1] 0]
set_property PROBES.FILE {} [get_hw_devices xc7z010_1]
set_property FULL_PROBES.FILE {} [get_hw_devices xc7z010_1]
set_property PROGRAM.FILE $bitstream [get_hw_devices xc7z010_1]
program_hw_devices [get_hw_devices xc7z010_1]
refresh_hw_device [lindex [get_hw_devices xc7z010_1] 0]
