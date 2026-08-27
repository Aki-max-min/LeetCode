class Solution:
    def lexGreaterPermutation(self, s, target):
        n = len(s)

        # Count characters in s
        cnt = [0] * 26

        for ch in s:
            cnt[ord(ch) - ord('a')] += 1

        # Try changing position i, from right to left
        for i in range(n - 1, -1, -1):

            # Check whether target[0:i] can be formed
            used = [0] * 26
            possible = True

            for j in range(i):
                x = ord(target[j]) - ord('a')
                used[x] += 1

                if used[x] > cnt[x]:
                    possible = False
                    break

            if not possible:
                continue

            # Remaining characters after forming target[0:i]
            rem = cnt[:]

            for c in range(26):
                rem[c] -= used[c]

            # Find smallest character > target[i]
            x = ord(target[i]) - ord('a')

            for c in range(x + 1, 26):

                if rem[c] > 0:
                    ans = target[:i]

                    # Make this position greater
                    ans += chr(c + ord('a'))

                    rem[c] -= 1

                    # Add remaining characters in sorted order
                    for d in range(26):
                        ans += chr(d + ord('a')) * rem[d]

                    return ans

        return ""