# Heredoc Functionality Implementation

This implementation adds complete heredoc functionality to the minishell project with variable expansion for quoted content, following 42 Norminette style guidelines.

## Key Features

### 1. Heredoc Detection and Parsing
- **`has_heredoc()`**: Detects `<<` operator in command lines
- **`get_heredoc_delimiter()`**: Extracts the delimiter string following `<<`
- **`remove_heredoc_from_line()`**: Removes heredoc part from command line for normal processing

### 2. Variable Expansion in Quoted Content
- **`is_quoted()`**: Checks if a line begins and ends with matching quotes (' or ")
- **`expand_variables()`**: Expands environment variables in `$VAR` format
- **`process_heredoc_line()`**: Main processing function that:
  - Detects quoted content
  - Extracts inner content from quotes
  - Expands variables within quoted content
  - Re-wraps expanded content with original quotes

### 3. Helper Functions
- **`ft_strjoin_char()`**: Custom libft extension to join string with single character
- **`read_heredoc()`**: Main heredoc reader that collects input until delimiter

## How It Works

1. **Command Parsing**: When a command line contains `<<`, the system:
   - Extracts the delimiter
   - Removes the heredoc portion from the command
   - Prepares to read heredoc input

2. **Input Processing**: For each heredoc line:
   - Checks if line begins and ends with quotes
   - If quoted: extracts content, expands variables, re-wraps with same quotes
   - If not quoted: keeps line as-is

3. **Variable Expansion**: When processing quoted content:
   - Scans for `$VARIABLE` patterns
   - Looks up environment variables
   - Substitutes values preserving quote context

## Example Usage

```bash
# Basic heredoc
cat << EOF
Hello World
EOF

# Variable expansion in quotes
export USER="John"
cat << EOF
"Hello $USER"
'Welcome $USER'
EOF
```

The implementation correctly handles:
- Double quotes (`"$VAR"`) → expands to `"expanded_value"`
- Single quotes (`'$VAR'`) → expands to `'expanded_value'` 
- Mixed quoted and unquoted content
- Multiple variables per line
- Environment variable lookup

## Code Structure

- **heredoc.c**: Complete heredoc implementation
- **token.c**: Enhanced tokenizer with heredoc detection
- **main.c**: Integration with main shell loop
- **minishell.h**: Function declarations

All functions follow 42 Norminette standards with proper error handling, memory management, and clear documentation.