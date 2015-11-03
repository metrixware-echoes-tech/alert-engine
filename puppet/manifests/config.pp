# Private class
class echoes_alert_engine::config inherits echoes_alert_engine {
  if $caller_module_name != $module_name {
    fail("Use of private class ${name} by ${caller_module_name}")
  }

  $config_file    = "${echoes_alert_engine::install_dir}/etc/engine.conf"
  $default_file   = "/etc/default/${echoes_alert_engine::service_name}"
  $init_file      = "/etc/init.d/${echoes_alert_engine::service_name}"
  $logrotate_file = "/etc/logrotate.d/${echoes_alert_engine::service_name}"

  file { $config_file:
    ensure  => 'file',
    owner   => 0,
    group   => 0,
    mode    => '0644',
    content => template("${module_name}/${echoes_alert_engine::branch}/${echoes_alert_engine::version}/engine.conf.erb"),
  }

  file { $default_file:
    ensure  => 'file',
    owner   => 0,
    group   => 0,
    mode    => '0644',
    content => template("${module_name}/${echoes_alert_engine::branch}/${echoes_alert_engine::version}${default_file}"),
  }

  file { $init_file:
    ensure  => file,
    owner   => 0,
    group   => 0,
    mode    => '0755',
    content => template("${module_name}/${echoes_alert_engine::branch}/${echoes_alert_engine::version}${init_file}.erb"),
  }

  file { $logrotate_file:
    ensure => 'file',
    owner  => 0,
    group  => 0,
    mode   => '0644',
    source => "puppet:///modules/${module_name}/${echoes_alert_engine::branch}/${echoes_alert_engine::version}${logrotate_file}",
  }



}
