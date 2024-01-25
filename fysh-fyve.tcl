# TODO: Add Zybo constraints

set script_path [ file dirname [ file normalize [ info script ] ] ]
set project_name "fysh-fyve"
set project_directory $script_path/proj
set part_number "xc7z010clg400-1"

create_project -force $project_name $project_directory -part $part_number

set_property target_language VHDL

add_files -fileset sources_1 [glob -directory $script_path/core/ *.vhd]
set_property top topmodule [get_filesets {sources_1}]

add_files -fileset sim_1 [glob -directory $script_path/test/ *.vhd]
set_property top topmodule_tb [get_filesets {sim_1}]

set_property file_type {VHDL 2008} [get_files -of [get_filesets {sources_1 sim_1}]]
