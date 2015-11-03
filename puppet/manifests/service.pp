# Private class
class echoes_alert_engine::service inherits echoes_alert_engine {
  if $caller_module_name != $module_name {
    fail("Use of private class ${name} by ${caller_module_name}")
  }

  $monit_file = "/etc/monit/conf.d/${echoes_alert_engine::service_name}"

  service { $echoes_alert_engine::service_name:
    ensure     => $echoes_alert_engine::service_ensure,
    enable     => $echoes_alert_engine::service_enable,
    hasrestart => true,
    hasstatus  => true,
  }->
  monit::check { $echoes_alert_engine::service_name:
    content => template("${module_name}/${echoes_alert_engine::branch}/${echoes_alert_engine::version}${monit_file}.erb"),
  }

}
