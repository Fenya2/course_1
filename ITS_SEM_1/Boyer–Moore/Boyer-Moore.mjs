import fs from "fs";

export default function findSubstrUsingBoyerMoore(pattern, heuristic)
{
    if(typeof pattern !== "string" && !(pattern instanceof String))
        return 1;
    if(pattern.length > this.length)
        return [];

    function getN(pattern) // таблица наиболее правых вхождений
    {
        let N = {};
        for(let i = 0; i < pattern.length; i++)
            N[pattern[i]] = i;
        return N;
    }

    switch(heuristic)
    {
        case 0: // bad character
        {
            let N = getN(pattern);
            let res = [];
            let match = true;
            for(let i = 0; i < this.length - pattern.length + 1;)
            {
                match = true;
                for(let j = pattern.length - 1; j >= 0; j--)
                {
                    if(pattern[j] !== this[j+i])
                    {
                        match = false;
                        if(!N.hasOwnProperty(this[i+j]))
                        {
                            i += pattern.length;
                            break;
                        }
                        i+= Math.max(pattern.length - (N[this[i+j]] + j), 1);
                        break;
                    }
                }
                if(match)
                {
                    res.push(i);
                    i++;
                }
            }
            return res;
        }
        case 1: // good suffix
        {
            let result = [];
            let N = [];
            for (let j = 0; j < pattern.length; j++)
                N[pattern.charAt(j)] = j + 1;

            let rpr = [];
            let pattern_ext = '';

            for (let i = 0; i < pattern.length; i++)
                pattern_ext += '*';

            pattern_ext += pattern;

            function compare(t1, t2)
            {
                for (let i = 0; i < t1.length; i++)
                {
                    if (t1[i] !== '*' && t2[i] !== '*' && t1[i] !== t2[i])
                        return false;
                }
                return true;
            }

            for (let l = 0; l <= pattern.length; l++)
            {
                rpr[l] = pattern.length;
                let k = pattern.length;
                while (true)
                {
                    if ((k <= pattern.length - l )
                        && compare(pattern_ext.slice(k + pattern.length - 1, k + pattern.length + l - 2 + 1), pattern.slice(pattern.length - l, pattern.length - 1 + 1))
                        && ( k>1 && pattern[k-2] !== pattern[pattern.length-l-1] || k<=1 ))
                            break;
                    k--;
                }
                rpr[l] = k;
            }

            let shift2 = [];

            for (let l = 0; l <= pattern.length; l++)
                shift2[l] = pattern.length - rpr[l] - l + 1;

            for (let i = 0; i <= this.length - pattern.length;)
            {
                let l = 0
                while (l < pattern.length){
                    if  (this[i + pattern.length - l - 1] !== pattern[pattern.length - l - 1])
                        break
                    l++;
                }

                if (l === pattern.length)
                    result.push(i);

                let ch = this[i + pattern.length - l - 1];
                let shift1;
                if (N[ch])
                    shift1 = Math.max(pattern.length - N[ch] - l, 1)
                else
                    shift1 = Math.max(pattern.length - l, 1)

                let shift = Math.max(shift1, shift2[l]);
                i += shift;
            }
            return result;
        }
        default:
            console.log("Error in type of heuristic");
            break;
    }
}
