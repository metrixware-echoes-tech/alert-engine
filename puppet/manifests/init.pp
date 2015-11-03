class echoes_alert_engine (
  $api_host          = $echoes_alert_engine::params::api_host,
  $api_port          = $echoes_alert_engine::params::api_port,
  $api_https         = $echoes_alert_engine::params::api_https,
  $branch            = $echoes_alert_engine::params::branch,
  $database_host     = $echoes_alert_engine::params::database_host,
  $database_name     = $echoes_alert_engine::params::database_name,
  $database_user     = $echoes_alert_engine::params::database_user,
  $database_password = $echoes_alert_engine::params::database_password,
  $install_dir       = $echoes_alert_engine::params::install_dir,
  $log_dir           = $echoes_alert_engine::params::log_dir,
  $log_filename      = $echoes_alert_engine::params::log_filename,
  $service_enable    = $echoes_alert_engine::params::service_enable,
  $service_ensure    = $echoes_alert_engine::params::service_ensure,
  $service_name      = $echoes_alert_engine::params::service_name,
  $version           = $echoes_alert_engine::params::version,
) inherits echoes_alert_engine::params {
  validate_string($api_host)
  validate_integer($api_port, 65535, 1)
  validate_bool($api_https)
  validate_string($branch)
  validate_string($database_host)
  validate_string($database_name)
  validate_string($database_user)
  validate_string($database_password)
  validate_absolute_path($install_dir)
  validate_absolute_path($log_dir)
  validate_string($log_filename)
  validate_bool($service_enable)
  validate_string($service_ensure)
  validate_string($service_name)
  validate_string($version)

  require echoes_alert_dbo

  $log_file = "${log_dir}/${log_filename}"

  anchor { "${module_name}::begin": } ->
  class { "${module_name}::install": } ->
  class { "${module_name}::config": } ~>
  class { "${module_name}::service": } ->
  anchor { "${module_name}::end": }
}
