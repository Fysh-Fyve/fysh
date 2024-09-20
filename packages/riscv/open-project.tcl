set script_path [ file dirname [ file normalize [ info script ] ] ]
set project_directory $script_path/proj

open_project $project_directory/fysh-fyve.xpr
