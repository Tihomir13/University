const numbers = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9'];

function isValidConst(string) {
  let isValid = false;

  if (numbers.includes(string[0]) && string[0] != '0') {
    isValid = true;
  } else {
    console.log(`The constant is not valid`);
    return;
  }

  for (let i = 1; i < string.length; i++) {
    if (numbers.includes(string[i])) {
    } else {
      isValid = false;
      break;
    }
  }

  console.log(`The constant is ${isValid ? 'valid' : 'not valid'}`);
}

isValidConst('023232');
