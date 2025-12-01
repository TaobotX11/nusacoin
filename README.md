Development is now occurring on the Nusacoin-Core repo
As of 2022, development has now moved to the Taobot organization, under the Nusacoin repo


What is Nusacoin?
Nusacoin (CICX) is a highly secure, decentralized, distributed and time-tested global blockchain that was founded in early 2019 with a focus on cyber security, payments & secure communications technologies.

For more information, as well as an immediately useable, binary version of the Nusacoin Core software, see https://taobot.org

Nusacoin Overview

Launch Date: March 7th, 2019

Blockchain Type: Public, Decentralized, UTXO based, X11-Algorithm

Ticker Symbol: CICX

Genesis Block Hash: "Detik 26/Aug/2019 Gegara Ditipu Bitcoin, Pria Ini Balas Curi Rp 160 Juta dan Aniaya Korban"

Community Block Hash (71008) : <tt>a946c0334e33cb70c5f0c4dbabb791a7d50c06031b8ade954b23caa59b19fa0e</tt>

<tt>
Ya Lal Wathan diciptakan oleh KH. Abdul Wahab Chasbullah pada tahun 1916 saat mendirikan organisasi gerakan bernama Syubanul Wathan dan diijazahkan oleh (alm) KH. Maemon Zubair Tahun pada tahun 2012.
 
ياَ لَلْوَطَنْ ياَ لَلْوَطَن ياَ لَلْوَطَنْ
Ya Lal Wathon Ya Lal Wathon Ya Lal Wathon
 
حُبُّ الْوَطَنْ مِنَ اْلإِيمَانْ
Hubbul Wathon minal Iman
 
وَلاَتَكُنْ مِنَ الْحِرْماَنْ
Wala Takum minal Hirman
 
اِنْهَضوُا أَهْلَ الْوَطَنْ
Inhadlu Alal Wathon
 
اِندُونيْسِياَ بِلاَدى
Indonesia Biladi
 
أَنْتَ عُنْواَنُ الْفَخَاماَ
Anta ‘Unwanul Fakhoma
 
 
كُلُّ مَنْ يَأْتِيْكَ يَوْماَ
Kullu May Ya’tika Yauma
 
طَامِحاً يَلْقَ حِماَمًا
Thomihay Yalqo Himama
</tt>

Max Total Supply: ~18 Million Nusacoins

Current Supply: 8,974,200 CICX (June 2025)

Block Reward Reduction: every 600,000 block

Current Block Reward: 8 CICX (June 2025)

Mining Algorithms: X11

Block Interval: ~ 6 minutes

Difficulty Retarget: Every 2016 Block

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