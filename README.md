Development is now occurring on the Nusacoin-Core repo
As of 2025, development has now moved to the Taobot organization, under the Nusacoin repo


What is Nusacoin?
Nusacoin (NUX) is a highly secure, decentralized, distributed and time-tested global blockchain that was founded in early December 2025 with a focus on cyber security, payments & secure communications technologies.

For more information, as well as an immediately useable, binary version of the Nusacoin Core software, see https://taobot.org

Nusacoin Overview

Launch Date: December 1st, 2025

Blockchain Type: Public, Decentralized, UTXO based, X11-Algorithm

Ticker Symbol: NUX

Genesis Block Hash: "Hari ini 01/Dec/2025, NUSA Lahir dari Kepercayaan, Transparansi dan Kebersamaan Rakyat."

Community Block Hash (0) : <tt>0000017123d6f996589bc2e58bb5502218012ac7f527ab599a3be84c1951c669</tt>

Max Total Supply: ~18 Million Nusacoins

Current Supply: 50 NUX (Dec 2025)

Block Reward Reduction: every 300,000 block

Halving Estimated : every 3.7 year

Current Block Reward: 30 NUX (June 2025)

Mining Algorithms: X11

Block Interval: ~ 6 minutes

Difficulty Retarget: Every 3360 Block (2 weeks)

SegWit Support: Yes.

Softforks: SegWit, CSV, NVersionBits

You can mine Nusacoin on X11 algorithms. This allows for much greater decentralization than other blockchains. 
making Nusacoin much more secure against PoW attacks.

Nusacoin vs Bitcoin
Security:

Nusacoin mining is much more decentralized.

Nusacoin mining algorithms can be changed out in the future to prevent centralization.

Nusacoin transactions occur much faster than Bitcoin transactions.
1-2 second transaction notifications.
6 minute Nusacoin blocks vs. 10 minute Bitcoin blocks*

Multi-Algorithm (X11): Employs a sequence of 11 different hashing algorithms, which can make it more resistant to certain types of attacks compared to using a single algorithm (SHA-256).

Has been adopted by some cryptocurrencies, like Dash, for its mining algorithm, potentially offering a more balanced approach to security and mining efficiency. 

License
Nusacoin Core is released under the terms of the MIT license. See COPYING for more information or see https://opensource.org/licenses/MIT.

Development Process
The develop branch is regularly built and tested, but is not guaranteed to be completely stable. Additionally, the develop branch represents ongoing development from which candidate releases will be cut. The master branch represents the current stable version currently in production. Tags are created regularly to indicate new official, stable release versions of Nusacoin Core. Finally, feature/{a-new-feature} branches represent current development destined for future releases.

The contribution workflow is described in CONTRIBUTING.md.

Testing
Automated Testing
Developers are required to write unit tests for new code, and to submit new unit tests for any old code that is changed. Unit tests can be compiled and run (assuming they weren't disabled in configure) with: make check. Further details on running and extending unit tests can be found in /src/test/README.md.

There are also regression and integration tests, written in Python, that are run automatically on the build server. These tests can be run (if the test dependencies are installed) with: test/functional/test_runner.py

The Travis CI system makes sure that every pull request is built for Windows, Linux, and macOS, and that unit/sanity tests are run automatically.

Manual Quality Assurance (QA) Testing
Changes are required be tested by somebody other than the developer who wrote the code. This is especially important for large or high-risk changes. A test plan must be included with the pull request description if testing the changes is not straightforward.