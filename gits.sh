echo "1:$1 2:$2 3:$3 4:$4 5:$5 6:$6 7:$7"
URL=$(cat $1)
echo $URL
curl -s $URL -o $2
cp $2 /libs/$2
