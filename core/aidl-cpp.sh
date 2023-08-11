#! /bin/sh

base_include_dir=$1
input_dir=$2
header_dir=$3
source_dir=$4

include_dir="-I $base_include_dir"

for dir in $(ls -d $base_include_dir/*) 
do
    if [ -d $dir ]
    then
        include_dir="$include_dir -I $dir"
    fi
done

#echo $include_dir
#exit

if [ -d $input_dir ]
then 
    find $input_dir -name "*.aidl" -exec aidl-cpp $include_dir {} $header_dir $source_dir ';'
fi

if [ -f $input_dir ]
then
    aidl-cpp $include_dir $input_dir $header_dir $source_dir
fi
