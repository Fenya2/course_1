let exp = process.argv[2];
let regExp = RegExp(/([+-]?\d+x\^\d+)+/);
let regExp2 = RegExp(/([+-]?\d+\.?\d+x\^\d+)(?=([+-]?\d+x\^\d+))/);
let res = regExp2.test(exp);
console.log(res);