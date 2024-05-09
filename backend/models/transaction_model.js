
const db = require('../dbtesti');

const transaction = {
    getAllTransaction: (callback) => {
        let sql = "SELECT * FROM transaction";
        db.query(sql, callback);
    },
    getOneTransaction(id, callback) {
        return db.query("SELECT * FROM transaction WHERE accountID=?", [id], callback);
    }
};


module.exports = transaction;