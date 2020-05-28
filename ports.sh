#!/bin/bash

# Read in the local configuration
. local-ports.sh

TASK=$1
PRE_COMMAND=""
COMMAND=""
LOG_FILE_PREFIX=""

UPLOAD_TASK="upload"
UPLOADFS_TASK="uploadfs"
MONITOR_TASK="monitor"
CLEAN_TASK="clean"
DEFAULT_TASK="default"

LOG_FILE_SUFFIX="log"

case "$TASK" in
  "$UPLOAD_TASK")
    PRE_COMMAND="platformio run"
    COMMAND="platformio run -t nobuild -t upload --upload-port"
    LOG_FILE_PREFIX="$UPLOAD_TASK"
    ;;
  "$UPLOADFS_TASK")
    PRE_COMMAND="platformio run -t buildfs"
    COMMAND="platformio run -t uploadfs --upload-port"
    LOG_FILE_PREFIX="$UPLOADFS_TASK"
    ;;
  "$MONITOR_TASK")
    COMMAND="./monitor.sh $MONITOR_BAUDRATE"
    LOG_FILE_PREFIX="$MONITOR_TASK"
    ;;
  "$CLEAN_TASK")
    rm $UPLOAD_TASK.*.$LOG_FILE_SUFFIX
    rm $UPLOADFS_TASK.*.$LOG_FILE_SUFFIX
    rm $MONITOR_TASK.*.$LOG_FILE_SUFFIX
    exit 0
    ;;
  "$DEFAULT_TASK")
    echo ${LOCAL_PORTS[$DEFAULT_PORT]}
    exit 0
    ;;
  *)
    echo $"Usage: $0 {$UPLOAD_TASK|$UPLOADFS_TASK|$MONITOR_TASK|$CLEAN_TASK|$DEFAULT_TASK}"
    exit 1
esac
  
CHILDREN=()
RUNNING=""
EXIT_CODE=0

# kill all children if killed
cleanup() {
  for i in ${!CHILDREN[@]}; do
    local CHILD=${CHILDREN[$i]}
    if [ "$CHILD" != "" ]; then
      kill $CHILD 2> /dev/null
      echo "${LOCAL_PORTS[$i]} $TASK stopped"
    fi
    local CHILD=${CHILDREN[$i]}
  done
}
trap cleanup EXIT

start() {
  if [ "$PRE_COMMAND" != "" ]; then
    $PRE_COMMAND
    local STATUS=$?
    if (( STATUS != 0 )); then
      exit $STATUS
    fi
  fi
  RUNNING=""
  for i in ${!LOCAL_PORTS[@]}; do
    local LOCAL_PORT=${LOCAL_PORTS[$i]}
    local LOG_FILE="$LOG_FILE_PREFIX.$i.$LOG_FILE_SUFFIX"
    local FULL_COMMAND="$COMMAND $LOCAL_PORT"
    echo "$FULL_COMMAND"
    $FULL_COMMAND >>$LOG_FILE 2>&1 &
    local CHILD=$!
    echo "${LOCAL_PORTS[$i]} $TASK started, logging to $LOG_FILE"
    CHILDREN+=($CHILD)
    RUNNING="$RUNNING $CHILD"
  done
}

# remove CHILDREN that are no loger running
check() {
  # check which CHILDREN have ended
  RUNNING=""
  for i in ${!CHILDREN[@]}; do
    local CHILD=${CHILDREN[$i]}
    if [ "$CHILD" != "" ]; then
      if kill -0 $CHILD 2> /dev/null; then
        RUNNING="$RUNNING $CHILD"
      else
        CHILDREN[$i]=""
        wait $CHILD
        local STATUS=$?
        if (( STATUS == 0 )); then
          echo "${LOCAL_PORTS[$i]} $TASK completed successfully"
        else 
          echo "${LOCAL_PORTS[$i]} $TASK failed with exit code $STATUS"
          EXIT_CODE=1
        fi
      fi
    fi
  done
}

# start children
start

# wait for children to exit
while [ "$RUNNING" != "" ]; do
  sleep 1
  check
done

# children have all exited so cancel trap to cleanup
trap - EXIT

exit $EXIT_CODE
