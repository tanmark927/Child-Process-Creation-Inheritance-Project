// Mark Tan
// child_process.cpp
// This program finds and replaces text within a given document using a child process.
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
#include <cstdlib>
using namespace std;

string sample_doc = 
"A digital divide represents the difference between those who can access technology and those who cannot. Access types include physical access, the knowledge to use technology and the ability to use it. At a time in which technology has a strong impact on modern society, ranging from electricity to transportation, it is important for a population to have widespread access to these resources. However there are still those who cannot access these technologies in populated areas ranging from rural areas to third world countries. These individuals are considered to be part of the losing side of the divide.\n"
"Given the heavy reliance on technology in modern times, those on the winning side of the divide are obligated to narrow the gap between them and those on the losing side. In fact, there have been a few attempts to shorten the gap between both sides. Kendall Russell’s article, “OneWeb to Help Bridge Digital Divide in Saudi Arabia”, describes a collaboration between global communications company OneWeb and the Kingdom of Saudi Arabia intent on developing solutions for broadband access in over 200,000 homes. Both parties are doing this to expand coverage of high-speed Internet and improve the infrastructure of communication and data networks. Since the goals of this collaboration impact rural areas the most, it allows the country as a whole to transition to a territory that has a majority of people with access to technology. Therefore this is an example in which the winning side should narrow the gap.\n"
"Narrowing the cap can occur in other scenarios as well. Peter Ryan’s article, “NBN trials cheaper technology to reduce digital divide in communities”, elaborates on the National Broadband Network Company’s plan to use a fibre-to-the-curb (FTTC) technology to bring access to more individuals in Australia. NBN Co. is attempting to provide FTTC to all regions in the country including those that have current forms of fibre connection that are more costly. This scenario shows that narrowing the gap does not necessarily mean that solutions have to be expensive. One issue that is apparent for this case is that the scope expands to a whole country instead of an area within it, so NBN will have to make their changes widespread even in areas that can access technology without FTTC. Also, while the predicted cost of FTTC might be less than the current forms of access, it still requires NBN to invest in enough resources to cover a full country.\n";

int main() {
long childPID;
int status; 
int replace_count = 0; 
size_t found;

for(;;){
string target, replacement;

cout << "Target String: ";
getline(cin, target);
if(target == string("!wq")) { break; }

cout << "Replacement String: ";
getline(cin, replacement);
if(replacement == string("!wq")) { break; }

//creates child
childPID = fork();

if(childPID == 0) { //child process
found = 0;

//finds and replaces text with a desired string
while((found = sample_doc.find(target, found)) != string::npos) { 
sample_doc.replace(found, target.length(), replacement);
found += replacement.length();
++replace_count;
}

if(replace_count <= 0) {
//resets found value for new find/replace procedure
found = 0;

//initiates infinite loop bug if replace_count is incorrect
for(;;) {
cout << "." << endl;
sample_doc.replace(found, target.length(), replacement);
found += replacement.length();
}
}
else { cout << sample_doc << endl; }

//sends replace_count value back to parent
return (replace_count);
exit(0);
}
else { //parent process
childPID = wait(&status);

/*Because only the child updates replace_count, parent must call	WEXITSTATUS(status) to access the replace_count value*/
if(WEXITSTATUS(status) > 0) {
//outputs the number of times of string replacement
cout << "Words replaced: " << WEXITSTATUS(status) << endl;
cout << endl;
}
}
}
exit(0);
}
