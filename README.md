


structure


[1 reasoning model, low thinking?]

`tree` +
`cat README.md` +

You will create a plan for completing this assignment. Specifify the files you need to see in order to make this plan in the following format:

```output
./myfile1.v
./myfile2
...
```

output just this output code block and nothing else; we will give them back to you in the next step
[/1]

[2 reasoning model, high thinking]

prev 2 messages +
`cat ...` +
Create the plan for completing this assignment
[/2]

(while true)
    
This stage has multiple different options

    [3]
    ```edit
    ./name_of_file_to_edit
    Full file with modifications (rest of file)
    ```

    The first line will be interpreted as the relative path of the file
    The rest of the file is treated as the full, new, updated file

    [/3]

    [4]
    ```test
    ```

    runs `make test`
    [/4]

    [5]
    ```submit
    ```
    Marks the assignment as completed and conclude. You will be unable to make actions once you use this command
    [/5]



    Output just one codeblock containing the operation and content if applicable, and nothing else

(end while)







