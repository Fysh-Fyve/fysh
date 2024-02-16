set script_path [ file dirname [ file normalize [ info script ] ] ]
set project_directory $script_path/proj

set_property incremental_checkpoint $project_directory/fysh-fyve.srcs/utils_1/imports/synth_1/topmodule.dcp [get_runs impl_1]
