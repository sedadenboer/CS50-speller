# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

A synonym for Silicosis and also the longest English word with a lemma.

## According to its man page, what does `getrusage` do?

Get resource usage like CPU time used, memory used etc.

## Per that same man page, how many members are in a variable of type `struct rusage`?

16

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

Probably uses less memory to deduct structures then to load the values of all members and do the calculations with those.

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

For each character in the file, check if it is alphabetic or an '. If so, add to word.
If it is longer then 45 characters, its not a word. If it is a number, it is not a word. Continue finding characters.
If it is a word, replace old word with newly found word and check if it is misspelled.

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

When using fscan f you can only find words with equal size as the used buffer.

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

Using const char *word/dictonary takes the pointer and prevents modification of the original word.
Only the copy of the word inside the function can be modified.
