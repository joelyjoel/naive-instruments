#! /bin/bash

for snapshot in snapshots/*; do
  echo $snapshot
  rms-graph "$snapshot"
  play "$snapshot"
done
