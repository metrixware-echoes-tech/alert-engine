# echoes-alert-engine

#### Table of Contents

1. [Overview](#overview)
2. [Module Description - What the module does and why it is useful](#module-description)
3. [Setup - The basics of getting started with wt](#setup)
    * [Setup requirements](#setup-requirements)
    * [Beginning with echoes_alert_engine](#beginning-with-echoes_alert_engine)
4. [Usage - Configuration options and additional functionality](#usage)
5. [Reference - An under-the-hood peek at what the module is doing and how](#reference)
6. [Limitations - OS compatibility, etc.](#limitations)
7. [Development - Guide for contributing to the module](#development)
8. [Contributors](#contributors)

## Overview

Puppet module to manage Echoes Alert Engine installation and configuration.

## Module Description

This module installs and configures Echoes Alert Engine.

## Setup

### Setup requirements

This module requires Wt to be installed.

You can use [echoes-wt](https://github.com/echoes-tech/puppet-wt) to install Wt.

The Engine resources (binaries, configuration files, etc.) should be located in the `files` or `templates` directories of the module, under the path `/$branch_name/$version_number/`.

### Beginning with echoes_alert_engine

```puppet
include 'echoes_alert_engine'
```

## Usage

An example of resource-like class declaration: 

```puppet
class {'echoes_alert_engine':
  branch  => 'develop',
  version => 'latest',
}
```
## Reference

### Classes

#### Public classes

* echoes_alert_engine: Main class, includes all other classes.

#### Private classes

* echoes_alert_engine::params: Sets parameter defaults.
* echoes_alert_engine::install: Handles the binary.
* echoes_alert_engine::config: Handles the configuration.
* echoes_alert_engine::service: Handles the service.

#### Parameters

The following parameters are available in the `::echoes_alert_engine` class:

##### `api_host`

Specifies the host of the Echoes Alert API. Valid options: string. Default value: 'ea-api'

##### `api_port`

Specifies the HTTP port of the Echoes Alert API. Valid options: integer >= 1. Default value: 443

##### `api_https`

Specifies whether the Echoes Alert API use HTTPs. Valid options: boolean. Default value: true

##### `branch`

Tells Puppet which branch to choose to install Engine. Valid options: string. Default value: 'master'

##### `log_dir`

Specifies what is the Echoes Alert log directory. Valid options: path. Default value: '/var/log/echoes-alert'

##### `log_filename`

Tells Puppet what Wt log file to create. Valid options: string. Default value: 'engine.log'

##### `service_ensure`

Tells Puppet whether the Echoes Alert Engine service should be running. Valid options: 'running' or 'stopped'. Default value: 'running'

##### `service_manage`

Tells Puppet whether to manage the Echoes Alert Engine service. Valid options: 'true' or 'false'. Default value: 'true'

##### `service_name`

Tells Puppet what Echoes Alert Engine service to manage. Valid options: string. Default value: 'ea-engine'

##### `version`

Tells Puppet which version to choose to install Engine. Valid options: 'latest' or a specific version number. Default value: 'latest'

## Limitations

Debian family OSes is officially supported. Tested and built on Debian.

##Development

[Echoes Technologies](https://www.echoes-tech.com) modules on the Puppet Forge are open projects, and community contributions are essential for keeping them great.

## Contributors

The list of contributors can be found at: https://forge.echoes-tech.com/projects/engine/repository/statistics#statistics-contributors

