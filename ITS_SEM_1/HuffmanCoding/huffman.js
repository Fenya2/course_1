class TreeNode { //parent and Sons([]) must have a Node type
    constructor(letter, weight, parent, sons, num, isUsed) {
        this.letter = letter;
        this.weight = weight;
        this.parent = parent;
        this.sons = sons;
        this.num = num;
        this.isUsed = isUsed;
    }
}

function makeSeries(sequence) {
    let series = {};
    for(let i = 0; i < sequence.length; i++) {
        if(!series[sequence.charAt(i)]) series[sequence.charAt(i)] = 1;
        else series[sequence.charAt(i)]++;
    }
    return Object.entries(series); // return array type of [[letter, quantity],...]
}

function makeLeaves(series) {
    let leaves = [series.length];
    for(let i = 0; i < series.length; i++) {
        leaves[i] = new TreeNode(series[i][0], series[i][1], null, null, null, false); //num param sets in a tree
    }
    return leaves;
}

class Tree {

    constructor(treeLeaves) {
        this._treeLeaves = treeLeaves;
        this._tree = [];
        this._codeTable = {};

        if(this._treeLeaves.length === 1) {
            this._codeTable[this._treeLeaves[0].letter] = '0';
            return;
        }

        for(let i = 0; i < this._treeLeaves.length; i++) { // add leaves
            this._treeLeaves[i].num = i;
            this._tree.push(this._treeLeaves[i]);
        }
        while(this.have2UnusedNodes()) { // tree creating
            let unusedNodes = [];
            for (let i = 0; i < this._tree.length; i++) { // find unused nodes
                if (!this._tree[i].isUsed) {
                    unusedNodes.push(this._tree[i]);
                }
            }
            let NodesWeights = new Array(unusedNodes.length);
            for (let i = 0; i < unusedNodes.length; i++) {
                NodesWeights[i] = unusedNodes[i].weight;
            }

            let minWeightsIndexes = get2minimalNumsIndexes(NodesWeights);
            let son1 = unusedNodes[minWeightsIndexes[0]];
            let son2 = unusedNodes[minWeightsIndexes[1]];
            let sons = [son1, son2];
            let sonsWeight = son1.weight + son2.weight;

            this._tree.push(new TreeNode(`${son1.letter}${son2.letter}`, sonsWeight, null, sons, 0, false));
            this._tree[this._tree.length-1].num = this._tree.length - 1;
            this._tree[son1.num].isUsed = true;
            this._tree[son2.num].isUsed = true;
            this._tree[son1.num].parent = this._tree[this._tree.length - 1]; //link the son1 with new parent
            this._tree[son2.num].parent = this._tree[this._tree.length - 1]; //link the son2 with new parent
        }
    }
    getNodeCode(code, treeNode) {
        this.code = code;
        if(treeNode.parent === null) { //if in root of the tree
            return this.code.split("").reverse().join().replace(/[\s,]/g, '');
        }
        if(treeNode.parent.sons[0].num  === treeNode.num) {
            return this.getNodeCode(this.code+='0', treeNode.parent);
        }
        else if(treeNode.parent.sons[1].num  === treeNode.num) {
            return this.getNodeCode(this.code+='1', treeNode.parent);
        }
    }
    generateCodeTable(){
        for(let i = 0; i < this._treeLeaves.length; i++) {
            this._codeTable[`${this._tree[i].letter}`] = this.getNodeCode('', this._tree[i]);
        }
        return this._codeTable;
    }
    getCodeTable() {
        if(Object.keys(this._codeTable).length === 0) return this.generateCodeTable();
        return this._codeTable;
    }

    have2UnusedNodes() { // 2 because last parent node will be unused
        let counter = 0;
        for(let i = 0; i < this._tree.length; i++) {
            if(!this._tree[i].isUsed) counter++;
            if(counter === 2) return true;
        }
        return false;
    }
}

class HuffmansCoder {
    constructor(codeTable) {
        this.codeTable = codeTable;
        this.decodeTable = {};
        Object.entries(codeTable).forEach((value) =>{ // make decode table (code:letter)
            this.decodeTable[value[1]] = value[0];
        })
    }

    encode(inputSequence) {
        let outputSequence =  '';
        for(let i = 0; i < inputSequence.length; i++) {
            if(this.codeTable[`${inputSequence.charAt(i)}`]) {
                outputSequence += this.codeTable[`${inputSequence[i]}`];
            }
            else throw Error(`there is not [${inputSequence.charAt(i)}] symbol in code table`);
        }
        return outputSequence;
    }

    encodeToFile(inputSequence, fileName) {
        let encodedSequence =  this.encode(inputSequence);
        let divisionReminder = encodedSequence.length % 8;
        encodedSequence += '0'.repeat(8 - divisionReminder);
        let fileOutputSequence = String.fromCharCode(divisionReminder);
        for(let i = 0; i < encodedSequence.length; i+=8) {
            fileOutputSequence += String.fromCharCode(parseInt(encodedSequence.slice(i, i+8),2));
        }
        require('fs').writeFileSync(fileName, fileOutputSequence);
        return fileOutputSequence;
    }

    decodeFromFile(inputFilename) {
        const fs = require('fs');
        let inputSequence = fs.readFileSync(inputFilename).toString();
        let codeSequence = '';
        let divisionReminder = inputSequence.charCodeAt(0);
        for(let i = 1; i < inputSequence.length; i++) { //todo length-1 ?????????????
            let byteCode = inputSequence.charCodeAt(i).toString(2);
            while (byteCode.length < 8) {
                byteCode = '0'.concat(byteCode);
            }
            codeSequence += byteCode;
        }
        codeSequence = codeSequence.slice(0, (divisionReminder-8));
        return this.decode(codeSequence);
    }

    decode(inputSequence) { //todo can add check that code (letters or number?) in inputSequence decodes in decodeTable.
        let outputSequence = '';
        for(let i = 0; i < inputSequence.length; i++) {
            let charCodeFound = false;
            let charCode = '';
            while (!charCodeFound && i < inputSequence.length) {
                charCode += inputSequence.charAt(i);
                if(this.decodeTable[`${charCode}`]){
                    outputSequence += this.decodeTable[`${charCode}`];
                    charCodeFound = true;
                }
                else i++;
            }
        }
        return outputSequence;
    }

    saveCodeTable(fileName) {
        try {
            require('fs').writeFileSync(fileName, JSON.stringify(this.codeTable));
        } catch (e) {
            console.error(e.message);
            return null;
        }
        return this.codeTable;
    }
}

function get2minimalNumsIndexes(nums) { //min nums.length - 3. Return minimal nums indexes in array(minmin, min)
    let minmin = nums[0] <= nums[1] ? [0,nums[0]] : [1, nums[1]]; // [index in nums, value]
    let min = minmin[1] === nums[0] ? [1,nums[1]] : [0, nums[0]]; // [index in nums, value]
    for(let i = 2; i < nums.length; i++) {
        if(minmin[1] > nums[i]) {
            min = minmin;
            minmin = [i,nums[i]];
        }
        else if(min[1] > nums[i]) min = [i, nums[i]];
    }
    return [minmin[0],min[0]];
}

function getHelp() {
    console.log(require('fs').readFileSync('Help.txt').toString());
}

function getInputSequence(clArg) {
    let inputSequence;
    try {
        inputSequence = clArg;
        if (!inputSequence) throw new SyntaxError("Enter sequence you want to code");
    }
    catch (e) {
        console.error(e.message);
        getHelp();
        return null;
    }
    if(inputSequence.match(/^!/g)) inputSequence = inputSequence.replace("!", '');
    else {
        try {
            inputSequence = require('fs').readFileSync(clArg).toString();
        } catch (e) {
            console.error(e.message);
            getHelp();
            return null;
        }
    }
    return inputSequence;
}

let inputSequence = getInputSequence(process.argv[3]);
let coder = null;
let tree = {};
switch (process.argv[2]) {
    case 'code':
        tree = new Tree(makeLeaves(makeSeries(inputSequence)));
        coder = new HuffmansCoder(tree.getCodeTable());
        console.log(coder.codeTable);
        coder.saveCodeTable('codeTable.json');
        console.log(coder.encode(inputSequence));
        break;
    case 'decode':
        coder = new HuffmansCoder(JSON.parse(require('fs').readFileSync('codeTable.json').toString()));
        console.log(coder.decode(inputSequence));
        break;
    case 'codeToFile':
        tree = new Tree(makeLeaves(makeSeries(inputSequence)));
        coder = new HuffmansCoder(tree.getCodeTable());
        console.log(coder.codeTable);
        coder.saveCodeTable('codeTable.json');
        console.log(coder.encodeToFile(inputSequence, 'out.coded'));
        break;
    case 'decodeFromFile':
        coder = new HuffmansCoder(JSON.parse(require('fs').readFileSync('codeTable.json').toString()));
        console.log(coder.decodeFromFile(process.argv[3]));
        break;
    default: getHelp();
}