# time-logger
A time-logger, scanning for devices and adding entries of them to a database

At the moment this is more of a proof-of-concept than a fully fledged program.

[![Build Status](https://travis-ci.com/Deadolus/time-logger.svg?token=poxpihu9457b2ZrAvsoK&branch=master)](https://travis-ci.com/Deadolus/time-logger)


# Usage
This scans for devices and adds entries of the found devices to an sqlite database.
The idea is that you afterwards open the sqlite database with another program and generate reports of who was around when via the entries.

# Supported methods
So far scanning for bluetooth devices and scanning for (active) IPs in the network is supported.

# Prerequisites
nmap has to be installed and executable, a POSIX system is required (executes "rm" command)
Additionally following libraries are required: libbluetooth3 libbluetooth-dev libsqlite3-0 libsqlite3-dev
