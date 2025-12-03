#!/bin/bash
passed=0
failed=0

for file in test_import/*.rt; do
  printf "Running %-40s ... " "$(basename "$file")"

  # Capture stderr, discard stdout
  err=$(./bin/minirt "$file" 2>&1)
  if echo "$err" | grep -q "^Error.*"; then
    echo "PASS"
    passed=$((passed+1))
  else
    echo "FAIL"
    failed=$((failed+1))
    if [ -n "$err" ]; then
      echo "  Stderr:"
      echo "$err" | sed 's/^/    /' | head -n 5
    else
      echo "  Stderr: (empty)"
    fi
  fi
done

echo
echo "Summary: PASS=$passed  FAIL=$failed  TOTAL=$((passed+failed))"