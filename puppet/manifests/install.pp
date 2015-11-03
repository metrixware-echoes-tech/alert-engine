# Private class
class echoes_alert_engine::install inherits echoes_alert_engine {
  if $caller_module_name != $module_name {
    fail("Use of private class ${name} by ${caller_module_name}")
  }

  file { $echoes_alert_engine::install_dir:
    ensure => directory,
    owner  => 0,
    group  => 0,
    mode   => '0755'
  }->
  file { $echoes_alert_engine::binary_path:
    ensure => directory,
    owner  => 0,
    group  => 0,
    mode   => '0755'
  }->
  file { "${echoes_alert_engine::binary_path}/${echoes_alert_engine::service_name}":
    ensure => 'file',
    owner  => 0,
    group  => 0,
    mode   => '0755',
    source => "puppet:///modules/${module_name}/${echoes_alert_engine::branch}/${echoes_alert_engine::version}/engine",
  }

  file { "${echoes_alert_engine::install_dir}/etc":
    ensure => directory,
    owner  => 0,
    group  => 0,
    mode   => '0755'
  }

  file { $log_file:
    ensure => 'file',
    owner  => 0,
    group  => 0,
    mode   => '0644'
  }

}
