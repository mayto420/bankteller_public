
const db = require('../dbtesti');

const login={
  checkPin: function(cardNumber, pin, callback) {
      return db.query('SELECT pin FROM card WHERE cardNumber = ?',[cardNumber], callback); 
    }
};
          

module.exports = login;