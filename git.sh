#!/bin/bash

repository_url="https://github.com/appleiphonedddd/NDHU_Lab_of_Data_Structures_2023.git"
branch="main"
commit_message="upgrade"

git add .

git commit -m "$commit_message"

git pull origin $branch

git push origin $branch

echo "Pushed changes to $repository_url on branch $branch."
