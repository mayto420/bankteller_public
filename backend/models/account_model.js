const db = require('../dbtesti');

const accounts = {
    getAllAccounts: (callback) => {
        let sql = "SELECT * FROM accounts";
        db.query(sql, callback);
    },
    getOneAccounts(id, callback){
        return db.query("SELECT * FROM accounts WHERE accountID=?",[id],callback);
    },
    addAccounts(newAccounts,callback){
        return db.query("INSERT INTO accounts(accountID, total, card_type, userID,limits) VALUES(?,?,?,?,?)",[newAccounts.accountID,newAccounts.total, newAccounts.card_type, newAccounts.userID,newAccounts.limits],callback);
    },
    updateAccounts(id, updateAccounts,callback){
        return db.query("UPDATE accounts SET total=?,card_type=?, userID=?, limits=? WHERE accountID=?",[updateAccounts.total,updateAccounts.card_type, updateAccounts.userID,updateAccounts.limits, id],callback);
    },
    deleteAccounts(id,callback){
        return db.query("DELETE FROM accounts WHERE accountID=?",[id],callback);
    }
};


module.exports = accounts;

