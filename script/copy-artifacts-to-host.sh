#!/bin/bash

if [[ -z "${MUSIKCUBE_BUILD_HOST_IP}" ]]; then
    echo "no build host ip specified"
    exit
fi

if [[ -z "${MUSIKCUBE_BUILD_HOST_PW}" ]]; then
    echo "no build host pw specified"
    exit
fi

echo sshpass -p ${MUSIKCUBE_BUILD_HOST_PW} scp "$1/*" build@${MUSIKCUBE_BUILD_HOST_IP}:/home/build/ 2> /dev/null

ping -c 5 192.168.1.218
ping -c 5 ${MUSIKCUBE_BUILD_HOST_IP} 
traceroute 192.168.1.218

sshpass -p ${MUSIKCUBE_BUILD_HOST_PW} scp "$1/*" build@${MUSIKCUBE_BUILD_HOST_IP}:/home/build/ 2> /dev/null
