using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class 加血药 : MonoBehaviour
{

    public AudioClip collectClip;//拾取物品音效

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    ////<param name="other"></param>
    
    void OnTriggerEnter2D(Collider2D other) {
        角色移动 pc = other.GetComponent<角色移动>();
        if (pc!=null)
        {
            if(pc.MyCurrentHealth < pc.MyMaxHealth)
            {
                pc.ChangeHealth(2);
                AudioManager.instance.AudioPlay(collectClip);
                Destroy(this.gameObject);
            }
            Debug.Log("玩家碰到了草莓");
        }
    }
}
