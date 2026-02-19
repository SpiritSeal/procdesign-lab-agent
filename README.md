


TODO: You are building a minimal agent that will fully complete the coding part of the lab exercise in the ./assignment/ directory.

Use openrouter, and follow the structure provided.

Allowed models:
google/gemini-3.1-pro-preview
anthropic/claude-sonnet-4.6


the agent should run in a Docker container, and have a Makefile for spinning it up, etc, and should log to outside of the container


## structure


[1 heavy model, low thinking?]

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

[2 heavy model, high thinking]

prev 2 messages +
`cat ...` +
Create the plan for completing this assignment
[/2]

(while true)

[3]
This stage has multiple different options depending on what you put as ```option

    ```edit
    ./name_of_file_to_edit
    Full file with modifications (rest of file)
    ```

    The first line will be interpreted as the relative path of the file
    The rest of the file is treated as the full, new, updated file

    ```test
    ```

    runs `make test`
    ```submit
    ```
    Marks the assignment as completed and conclude. You will be unable to make actions once you use this command

    Output just one codeblock containing the operation and content if applicable, and nothing else



[/3]
(end while)







