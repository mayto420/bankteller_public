
const db = require('../dbtesti');

const customer = {
    getAllCustomer: (callback) => {
        let sql = "SELECT * FROM customer";
        db.query(sql, callback);
    },

    getOneCustomer(id, callback){
        return db.query("SELECT * FROM customer WHERE userID=?",[id],callback);
    },
    addCustomer(newCustomer,callback){
        return db.query("INSERT INTO customer(userID, firstname, lastname, password) VALUES(?,?,?,?)",[newCustomer.userID, newCustomer.firstname, newCustomer.lastname, newCustomer.password],callback);
    },
    updateCustomer(id, updateCustomer,callback){
        return db.query("UPDATE customer SET firstname=?, lastname=?, password=? WHERE userID=?",[updateCustomer.firstname, updateCustomer.lastname, updateCustomer.password, id],callback);
    },
    deleteCustomer(id,callback){
        return db.query("DELETE FROM customer WHERE userID=?",[id],callback);
    }
};

module.exports = customer;