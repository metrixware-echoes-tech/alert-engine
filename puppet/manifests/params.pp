# == Class: echoes_alert_engine::params
#
# This is a container class with default parameters for echoes_alert_engine classes.
class echoes_alert_engine::params {
  $name = 'engine'

  $api_host          = 'ea-api'
  $api_port          = 443
  $api_https         = true
  $branch            = 'master'
  $database_host     = '127.0.0.1'
  $database_name     = 'echoes'
  $database_user     = 'echoes'
  $database_password = 'echoes'
  $install_dir       = "/opt/echoes-alert/${name}"
  $log_dir           = '/var/log/echoes-alert',
  $log_filename      = 'engine.log',
  $service_enable    = true
  $service_ensure    = 'running'
  $service_name      = "ea-${name}"
  $version           = 'latest'

  $binary_path = "${install_dir}/bin"
}
