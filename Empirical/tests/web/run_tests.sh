source ../../third-party/emsdk_portable_repo/emsdk_portable/emsdk_env.sh
echo "Source loaded"
make
echo "compilation done"
for filename in js_utils.js JSWrap.js; 
do 
    node $filename; 
    if [ $? -gt 0 ]; 
    then 
	exit 1; 
    fi; 
done
