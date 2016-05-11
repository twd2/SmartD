#!/bin/bash

pushd `dirname $0`

python3 -m pip install . -r req.txt

pushd smartd

if [ ! -f secret.py ]; then
  cp secret.py.example secret.py
  echo '*** PLEASE EDIT smartd/secret.py ***'
  echo 'Press ENTER to continue.'
  read
fi

pushd static
bower install
popd

popd

popd

echo "Done. Command \`python3 -m smartd.server' to run."
