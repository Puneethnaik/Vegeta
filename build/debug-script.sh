all_cpp_files=$(find .. -type f -iregex '.*[\.h|\.cpp]')
prod_cpp_files=()
for file in $(find .. -type f -iregex '.*[\.h|\.cpp]');
do 
    if [[ $file == *"test"* ]]; then
        echo "skipping"
    elif [[ $file == *"git"* ]]; then
        echo "skipping"
    elif [[ $file == *"build"* ]]; then
        echo "skipping"
    else
        echo "Building"
        prod_cpp_files+=( $file )
    fi
    echo $file
done

g++ ${prod_cpp_files[@]} -o ../bin/prod/vegeta -g