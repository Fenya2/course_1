import * as fs from "fs";
import findSubstrUsingBoyerMoore from "./Boyer-Moore.mjs";

String.prototype.findSubstrUsingBoyerMoore = findSubstrUsingBoyerMoore;

if(process.argv[2] === '/?' || process.argv[2] === '--help' || process.argv[2] === '-h')
{
    console.log("Usage: node find.mjs text pattern heuristic");
    console.log("text arg is file with text.");
    console.log("heuristic: 0 - bad char");
    console.log("heuristic: 1 - good suffix");

    process.exit(0);
}

let str = fs.readFileSync(process.argv[2]).toString();
console.log(str.findSubstrUsingBoyerMoore(process.argv[3].toString(), Number(process.argv[4])));
